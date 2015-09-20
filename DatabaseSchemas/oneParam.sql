DROP TABLE IF EXISTS samples;

DROP TABLE IF EXISTS run;
CREATE TABLE run (
    runName varchar(255) KEY NOT NULL,
	runUUID VARCHAR(50) NOT NULL DEFAULT 'UUID()'
);

DROP TABLE IF EXISTS samples;
CREATE TABLE samples (
    iteration INT,
	runUUID VARCHAR(50) NOT NULL,
    logPosterior DOUBLE,
    theta double
);

