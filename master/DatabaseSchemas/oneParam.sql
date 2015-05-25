DROP TABLE IF EXISTS samples;

CREATE TABLE run (
    runId INT,
    params blob
);

CREATE TABLE samples (
    iteration INT KEY AUTO_INCREMENT,
    runId INT,
    theta DOUBLE
);





