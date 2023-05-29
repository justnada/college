CREATE DATABASE db_properti_latihan;
USE db_properti_latihan;
CREATE TABLE Branch(

	branchNo CHAR(4) NOT NULL,

	street VARCHAR(50) NOT NULL,

	city VARCHAR(50) NOT NULL,

	postcode VARCHAR(30) NOT NULL,

	PRIMARY KEY (branchNo),

	CONSTRAINT checkBranchNo CHECK(branchNo LIKE 'B00[0-9]')

)

ENGINE=INNODB DEFAULT CHARSET = latin1;


CREATE TABLE Staff(

staffNo CHAR(4) NOT NULL,

fName VARCHAR(20) NOT NULL,

lName VARCHAR(20) NOT NULL,

staffPosition ENUM('Manager', 'Assistant', 'Supervisor') NOT NULL,

sex ENUM('M', 'F') NOT NULL,

DOB DATE NOT NULL,

salary NUMERIC(10, 0) NOT NULL DEFAULT '0',

branchNo CHAR(4) NOT NULL,

PRIMARY KEY (staffNo),

KEY branchNo(branchNo), 

KEY FK_branch(branchNo),

KEY checkStaffNo(staffNo),

CONSTRAINT checkStaffNo CHECK(staffNo LIKE 'S[A-Z][0-9][0-9]'),

CONSTRAINT FK_branch FOREIGN KEY (branchNo) REFERENCES Branch(branchNo)

ON DELETE CASCADE

ON UPDATE CASCADE)

ENGINE=INNODB DEFAULT CHARSET = latin1;

CREATE TABLE PrivateOwner(

	ownerNo CHAR(4) NOT NULL,

	fName VARCHAR(25) NOT NULL,

	lName VARCHAR(25) NOT NULL,

	address VARCHAR (255) NOT NULL,

	telNo VARCHAR(13) NOT NULL,

	PRIMARY KEY (ownerNo),

	CONSTRAINT checkOwnerNo CHECK(ownerNo LIKE 'CO[0-9][0-9]')

)

ENGINE=INNODB DEFAULT CHARSET = latin1;


CREATE TABLE klien(

	clientNo CHAR(4) NOT NULL,

	fName VARCHAR(50) NOT NULL,

	lName VARCHAR(50) NOT NULL,

	telNo VARCHAR(13) NOT NULL,

	prefType ENUM('Flat', 'House') NOT NULL,

	maxRent INT(3) NOT NULL,

	PRIMARY KEY (clientNo),

	CONSTRAINT checkClientNo CHECK(clientNo LIKE 'CR[0-9][0-9]')

	)

ENGINE = INNODB DEFAULT CHARSET = latin1;


CREATE TABLE PropertyForRent(

	propertyNo CHAR(4) NOT NULL,

	street VARCHAR(100) NOT NULL,

	city VARCHAR(50) NOT NULL,

	postcode VARCHAR(50) NOT NULL,

	propertyType ENUM('House', 'Flat') NOT NULL,

	rooms INT(1) NOT NULL,

	rent INT(3) NOT NULL,

	ownerNo CHAR(4) NOT NULL,

	staffNo CHAR(4) NOT NULL,

	branchNo CHAR(4) NOT NULL,

	PRIMARY KEY (propertyNo),

	KEY checkPropertyNo (propertyNo),

	KEY FK_owner_propery (ownerNo),

	KEY FK_staff_propery(staffNo),

	KEY FK_branch_propery(branchNo),

	CONSTRAINT FK_owner_propery FOREIGN KEY (ownerNo) REFERENCES PrivateOwner(ownerNo),

	CONSTRAINT FK_staff_propery FOREIGN KEY (staffNo) REFERENCES Staff(staffNo),

	CONSTRAINT FK_branch_propery FOREIGN KEY (branchNo) REFERENCES Branch(branchNo),

	CONSTRAINT checkPropertyNo CHECK(propertyNo LIKE 'P[A-Z][0-9][0-9]')



)

ENGINE=INNODB DEFAULT CHARSET = latin1;


CREATE TABLE viewing(

	clientNo CHAR(4) NOT NULL,

	propertyNo CHAR(4) NOT NULL,

	viewDate DATE NOT NULL,

	clientComment VARCHAR(255) NOT NULL,

	PRIMARY KEY (clientNo, propertyNo),

	KEY FK_client_view (clientNo),

	KEY FK_property_view (propertyNo),

	CONSTRAINT FK_client_view FOREIGN KEY (clientNo) REFERENCES klien(clientNo),

	CONSTRAINT FK_property_view FOREIGN KEY (propertyNo) REFERENCES PropertyForRent(propertyNo)

)



ENGINE = INNODB DEFAULT CHARSET = latin1;


CREATE TABLE registration(

	clientNo CHAR(4) NOT NULL,

	branchNo CHAR(4) NOT NULL,

	staffNo CHAR(4) NOT NULL,

	date_joined DATE NOT NULL,

	PRIMARY KEY (clientNo, branchNo, staffNo),

	KEY FK_client_regis(clientNo),

	KEY FK_branch_regis(branchNo),

	KEY FK_staff_regis(staffNo),

	CONSTRAINT FK_client_regis FOREIGN KEY (clientNo) REFERENCES klien(clientNo),

	CONSTRAINT FK_branch_regis FOREIGN KEY (branchNo) REFERENCES Branch(branchNo),

	CONSTRAINT FK_staff_regis FOREIGN KEY (staffNo) REFERENCES Staff(staffNo)

)

ENGINE=INNODB DEFAULT CHARSET = latin1;