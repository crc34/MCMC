DROP TABLE IF EXISTS samples;

DROP TABLE IF EXISTS run;
CREATE TABLE run (
    runId INT KEY AUTO_INCREMENT,
    runName varchar(255)
   UID UNIQUEIDENTIFIER NOT NULL DEFAULT NEWID() 
);

DROP TABLE IF EXISTS samples;
CREATE TABLE samples (
    iteration INT KEY,
    runId INT,
    logPosterior DOUBLE,
    theta DOUBLE
);





