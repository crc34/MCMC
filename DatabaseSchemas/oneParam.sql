DROP TABLE IF EXISTS samples;

DROP TABLE IF EXISTS run;
CREATE TABLE run (
    runId INT KEY AUTO_INCREMENT,
    runName varchar(255),
    uuid VARBINARY(16)
);

DROP TABLE IF EXISTS samples;
CREATE TABLE samples (
    iteration INT,
    runId INT,
    logPosterior DOUBLE,
    theta DOUBLE
);





