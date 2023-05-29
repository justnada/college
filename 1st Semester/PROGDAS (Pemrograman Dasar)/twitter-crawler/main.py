import json
from urllib.parse import urlencode, quote
from datetime import datetime
import dateutil.relativedelta
import dateutil
import requests
from pytz import timezone


def _get_cursor(response):
    try:
        next_cursor = response['timeline']['instructions'][0]['addEntries']['entries'][-1]['content'][
            'operation']['cursor']['value']
    except KeyError:
        # this is needed because after the first request location of cursor is changed
        next_cursor = response['timeline']['instructions'][-1]['replaceEntry']['entry']['content']['operation'][
            'cursor']['value']
    return next_cursor

def _sanitize_query(_url, params):
    _serialQuery = ""
    _serialQuery = urlencode(params, quote_via=quote)
    _serialQuery = _url + "?" + _serialQuery
    return _serialQuery


def generate_headers():
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
    
    return  _headers


def get_tweets():
    _headers = generate_headers()
    cursor = '-1'
    d = datetime.now()
    d2 = d - dateutil.relativedelta.relativedelta(months=1)
    loop = 0
    keywords = ['resesi 2023', 'resesi indonesia', 'indonesia resesi', 'resesi ekonomi', 'resesi', 'ekonomi indonesia resesi', 'indonesia inflasi']
    
    # for keyword in keywords:
    for i in range(12):
        while True:
            loop += 1
            if loop % 50 == 0:
                _headers = generate_headers()
                
            url = "https://api.twitter.com/2/search/adaptive.json"
            params = [
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
            # q = f'"resesi" and "ekonomi" ("resesi" OR OR OR or OR OR OR "ekonomi" OR OR OR or OR OR OR "g20" OR OR OR or OR OR OR "G20" OR OR OR or OR OR OR "Ekonomi" OR OR OR or OR OR OR "Resesi" OR OR OR or OR OR OR "Recession" OR OR OR or OR OR OR "PertembuhanEkonomi" OR OR OR or OR OR OR "2023" OR OR OR or OR OR OR "Ekonomi2023" OR OR OR or OR OR OR "ekonomi") since:2021-11-18 until:2022-11-18'
            q = '"resesi 2023 indonesia" until:2022-12-31 since:2021-01-01'
            print(q)
            params.append(("q", q.strip()))
            _serialQuery = _sanitize_query(url, params)
            tryRequest = True
            
            while tryRequest:
                try:
                    response = requests.get(_serialQuery, headers=_headers)
                    tryRequest = False
                except Exception as e:
                    print('failed')
                    continue

            response = json.loads(response.text)
            tweets = response['globalObjects']['tweets']
            
            for key in tweets:
                result = {
                    'id': tweets[key]['id'],
                    'text': tweets[key]["full_text"],
                    'user': {
                        'id': response["globalObjects"]["users"][tweets[key]["user_id_str"]]['id'],
                        'name': response["globalObjects"]["users"][tweets[key]["user_id_str"]]['name'],
                        'description': response["globalObjects"]["users"][tweets[key]["user_id_str"]]['description'],
                        'location': response["globalObjects"]["users"][tweets[key]["user_id_str"]]['location'],
                        'followers_count' : response["globalObjects"]["users"][tweets[key]["user_id_str"]]['followers_count'],
                    },
                    'created_at': datetime.strptime(tweets[key]['created_at'], '%a %b %d %H:%M:%S %z %Y').strftime('%Y-%m-%d %H:%M:%S'),
                    'timestamp': int(datetime.now(tz=timezone('Asia/Jakarta')).timestamp()) * 1000
                }
                
                ## insert to elastic
                insert_es(result)
                print('\n')
                
            if len(response['globalObjects']['tweets']) == 0:
                break
            
            cursor = _get_cursor(response)
        

def insert_es(data):
    response = requests.post(f'http://192.168.24.132:9200/raw-twitter/_doc/{data["id"]}', json=data)
    print(response)
    print(response.url)
    print('sended to es', datetime.now())
    

if __name__ == "__main__":
    get_tweets()
    

