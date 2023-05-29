from concurrent.futures import ThreadPoolExecutor
import json
from urllib.parse import urlencode, quote
from datetime import datetime
import dateutil.relativedelta
import dateutil
from kafka import KafkaProducer
import requests

def updateStat(index_time, query, id_doc):
    response = requests.post(f'http://192.168.24.50:19200/rta-content.{index_time}/_update/{id_doc}', json=query)
    print(response.text)

producer = KafkaProducer(
    bootstrap_servers=["kafka01.production.bt:6667","kafka02.production.bt:6667","kafka03.production.bt:6667","kafka04.production.bt:6667"],
    value_serializer=lambda x:
    json.dumps(x).encode('utf-8'))

def checkData(idstr, index_time):
    response = requests.get(f'http://192.168.24.50:19200/rta-content.{index_time}/_doc/{idstr}')
    return response.status_code



def _get_cursor(response):
    try:
        next_cursor = response['timeline']['instructions'][0]['addEntries']['entries'][-1]['content'][
            'operation']['cursor']['value']
    except KeyError:
        # this is needed because after the first request location of cursor is changed
        next_cursor = response['timeline']['instructions'][-1]['replaceEntry']['entry']['content']['operation'][
            'cursor']['value']
    return next_cursor


def _sanitizeQuery(_url, params):
    _serialQuery = ""
    _serialQuery = urlencode(params, quote_via=quote)
    _serialQuery = _url + "?" + _serialQuery
    return _serialQuery


def generateHeaders():
    headers = {
        'authorization': 'Bearer AAAAAAAAAAAAAAAAAAAAANRILgAAAAAAnNwIzUejRCOuH5E6I8xnZz4puTs%3D1Zv7ttfk8LF81IUq16cHjhLTvJu4FA33AGWWjCpTnA',
    }

    response = requests.post('https://api.twitter.com/1.1/guest/activate.json', headers=headers)

    guest_token = json.loads(response.text)["guest_token"]

    bearer = 'Bearer AAAAAAAAAAAAAAAAAAAAANRILgAAAAAAnNwIzUejRCOuH5E6I8xnZz4puTs' \
             '%3D1Zv7ttfk8LF81IUq16cHjhLTvJu4FA33AGWWjCpTnA'

    _headers = {
        'authorization': bearer,
        'x-guest-token': guest_token,
    }
    return _headers


def getTweets(data):
    _headers = generateHeaders()

    cursor = '-1'
    d = datetime.now()
    d2 = d - dateutil.relativedelta.relativedelta(day=1)
    list_result = set()
    loop = 0
    for i in range(1):
        while True:
            loop += 1
            if loop % 50 == 0:
                _headers = generateHeaders()
            url = "https://api.twitter.com/2/search/adaptive.json"
            params = [
                # ('include_blocking', '1'),
                # ('include_blocked_by', '1'),
                # ('include_followed_by', '1'),
                # ('include_want_retweets', '1'),
                # ('include_mute_edge', '1'),
                # ('include_can_dm', '1'),
                # ('include_can_media_tag', '1'),
                # ('skip_status', '1'),
                # ('include_cards', '1'),
                ('include_ext_alt_text', 'true'),
                ('include_quote_count', 'true'),
                ('include_reply_count', '1'),
                ('tweet_mode', 'extended'),
                ('include_entities', 'true'),
                ('include_user_entities', 'true'),
                ('include_ext_media_availability', 'true'),
                ('send_error_codes', 'true'),
                ('simple_quoted_tweet', 'true'),
                ('count', 100000),
                ('query_source', 'typed_query'),
                ('pc', '1'),
                ('cursor', cursor),
                ('spelling_corrections', '1'),
                ('ext', 'mediaStats%2ChighlightedLabel'),
                ('tweet_search_mode', 'live'),  # this can be handled better, maybe take an argument and set it then
            ]
            q = f"from:{data} since:{str(d2)[0:10]}"
            q = q.strip()
            params.append(("q", q))
            _serialQuery = _sanitizeQuery(url, params)
            tryRequest = True
            while tryRequest:
                try:
                    response = requests.get(_serialQuery, headers=_headers)
                    print(q)
                    tryRequest = False
                except Exception as e:
                    continue

            response = json.loads(response.text)
            tweets = response['globalObjects']['tweets']
            for key in tweets:
                tweet = tweets[key]
                dt = tweet['created_at']
                index_time = datetime.strftime(datetime.strptime(dt,'%a %b %d %H:%M:%S +0000 %Y'), '%Y-%m-%d')
                status_check = checkData(tweet['id_str'], index_time)
                user_id_str = tweets[key]["user_id_str"]

                user = response["globalObjects"]["users"][user_id_str]
                if status_check == 200:
                    content_stat = {
                        'retweet_count': tweet['retweet_count'],
                        'favorite_count': tweet['favorite_count'],
                        'reply_count': tweet['reply_count'],
                        'quote_count': tweet['quote_count']
                    }
                    query = {
                        "doc": {
                            "content_stat": content_stat
                        }
                    }
                    try:
                        updateStat(index_time, query, tweet['id_str'])
                        print(tweet['id_str'], index_time)
                    except Exception as e:
                        print(e)
                else:
                    print('not_found')
                    user_id_str = tweets[key]["user_id_str"]
                    tweets[key]["user"] = response["globalObjects"]["users"][user_id_str]
                    extended_tweet = {}
                    extended_tweet["full_text"] = tweets[key]["full_text"]
                    extended_tweet["display_text_range"] = tweets[key]["display_text_range"]
                    extended_tweet["entities"] = tweets[key]["entities"]
                    tweets[key]["text"] = tweets[key]["full_text"]
                    tweets[key]["extended_tweet"] = extended_tweet
                    tweets[key]["user"] = response["globalObjects"]["users"][user_id_str]
                    tweets[key].pop("extended_entities", None)
                    tweets[key].pop("full_text", None)
                    tweets[key].pop("user_id", None)
                    tweets[key].pop("user_id_str", None)
                    tweets[key].pop("conversation_id", None)
                    tweets[key].pop("conversation_id_str", None)
                    tweets[key].pop("possibly_sensitive", None)
                    tweets[key].pop("possibly_sensitive_editable", None)
                    tweets[key].pop("supplemental_language", None)
                    # print(json.dumps(tweets[key]))
                    print(tweets[key])
                    producer.send('tw-post-v3', value=tweets[key])
                    now = datetime.now()
                    current_time = now.strftime("%H:%M:%S")
                    print(f"success send kafka {current_time}")
            if len(response['globalObjects']['tweets']) == 0:
                break
            cursor = _get_cursor(response)
            # print(cursor)
            # print(len(list_result))
        d2 = d - dateutil.relativedelta.relativedelta(day=1)


if __name__ == "__main__":
    list_user = ["prabowo", "aniesbaswedan", "puanmaharani_ri", "erickthohir", "ganjarpranowo"]
    futures = []
    with ThreadPoolExecutor(max_workers=30) as executor:
        for j in list_user:
            futures.append(executor.submit(getTweets, j))
