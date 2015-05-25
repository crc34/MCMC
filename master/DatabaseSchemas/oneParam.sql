DROP TABLE IF EXISTS samples;

DROP TABLE IF EXISTS run;
CREATE TABLE run (
    runId INT KEY AUTO_INCREMENT,
    runName varchar(255)
);

DROP TABLE IF EXISTS samples;
CREATE TABLE samples (
    iteration INT KEY AUTO_INCREMENT,
    runId INT,
    theta DOUBLE
);





