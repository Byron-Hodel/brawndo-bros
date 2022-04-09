# create database
create database if not exists BrawndoBros;

#use database
use BrawndoBros;

# create each table
create table Users (
	userId int NOT NULL AUTO_INCREMENT,
	email varchar(255),
	password varchar(255),
	lastLogin varchar(255),
	PRIMARY KEY (userId)
);

create table Plants (
	plantId int NOT NULL AUTO_INCREMENT,
	userId int,
	plantName varchar(255),
	plantSpecies varchar(255),
	plantImage varchar(255),
	soilMoistureThreshold varchar(255),
	soilMoistureCurrent varchar(255),
	soilMoistureDosage varchar(255),
	soilTempThreshold varchar(255),
	soilTempCurrent varchar(255),
	soilTempDosage varchar(255),
	ambientLightThreshold varchar(255),
	ambientLightCurrent varchar(255),
	ambientLightDosage varchar(255),
	PRIMARY KEY (plantId)
);

create table Events (
	eventId int NOT NULL AUTO_INCREMENT,
	plantId int,
	eventType varchar(255), #data or action
	eventSubtype varchar(255), #soilMoisture, soilTemp, ambientLight, image
	eventValue varchar(255),
	eventTime varchar(255),
	PRIMARY KEY (EventId)
);