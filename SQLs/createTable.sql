CREATE TABLE modified_date (
    date TEXT
)

CREATE TABLE trains (
    idx INTEGER PRIMARY KEY,
    number TEXT UNIQUE,
    traintype INTEGER,
    spottype INTEGER,
    origin INTEGER,
    destination INTEGER,
    departureTime TEXT,
    duration TEXT,
    price INTEGER,
    spots BLOB,
    FOREIGN KEY (origin) REFERENCES stations(idx),
    FOREIGN KEY (destination) REFERENCES stations(idx)
);

CREATE TABLE stations (
    idx INTEGER PRIMARY KEY,
    name TEXT UNIQUE
);

CREATE TABLE users (
    idx INTEGER PRIMARY KEY,
    username TEXT UNIQUE,
    password TEXT,
    phone TEXT,
    email TEXT,
    name TEXT,
    sex INTEGER,
    balance INTEGER
);

CREATE TABLE passengers (
    idx INTEGER PRIMARY KEY,
    user INTEGER,
    name TEXT,
    id TEXT,
    FOREIGN KEY (user) REFERENCES users(idx)
);

CREATE TABLE tickets (
    idx INTEGER PRIMARY KEY,
    user INTEGER,
    passenger INTEGER,
    train INTEGER,
    date TEXT,
    spot INTEGER,
    FOREIGN KEY (user) REFERENCES users(idx),
    FOREIGN KEY (passenger) REFERENCES passengers(idx),
    FOREIGN KEY (train) REFERENCES trains(idx)
);

CREATE TABLE admin (
    idx INTEGER PRIMARY KEY,
    username TEXT UNIQUE,
    password TEXT
);