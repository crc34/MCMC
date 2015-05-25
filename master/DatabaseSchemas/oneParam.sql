DROP TABLE IF EXISTS samples;

DROP TABLE IF EXISTS run;
CREATE TABLE run (
    runId INT,
    runName varchar(255),
    params blob
);

DROP TABLE IF EXISTS samples;
CREATE TABLE samples (
    iteration INT KEY AUTO_INCREMENT,
    runId INT,
    theta DOUBLE
);





