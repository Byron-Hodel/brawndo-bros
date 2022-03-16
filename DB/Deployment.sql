# create database
create database if not exists BrawndoBros;

#use database
use BrawndoBros;

# create each table
create table Users (
	userId int,
	email varchar(255),
	password varchar(255),
	lastLogin varchar(255)
);

create table Plants (
	userId int,
	plantNickName varchar(255),
	plantSpecies varchar(255),
	plantImage varchar(255),
	soilMoistureThreshold varchar(255),
	soilMoistureCurrent varchar(255),
	soilMoistureAction varchar(255),
	soilMoistureDosage varchar(255),
	soilTempThreshold varchar(255),
	soilTempCurrent varchar(255),
	soilTempAction varchar(255),
	soilTempDosage varchar(255),
	plantLightThreshold varchar(255),
	plantLightCurrent varchar(255),
	plantLightAction varchar(255),
	plantLightDosage varchar(255)
);

create table PlantEvents (
	plantId int,
	eventType varchar(255),
	eventValue varchar(255),
	eventTime varchar(255)
);

create table ActionEvents (
	plantId int,
	actionType varchar(255),
	actionTime varchar(255)
);