﻿#include <vector>

using namespace std;

// Define an array of person names
const vector<string> Names
{
    "Alice", "Bob", "Charlie", "David", "Eva",
    "Frank", "Grace", "Hannah", "Isaac", "Julia",
    "Kai", "Lena", "Max", "Nora", "Oliver",
    "Penelope", "Quincy", "Riley", "Sophia", "Theo",
    "Uma", "Victor", "Willa", "Xander", "Yara",
    "Zara", "Alex", "Bella", "Caleb", "Daisy",
    "Eli", "Fiona", "George", "Hazel", "Ian",
    "Jade", "Kevin", "Lily", "Mason", "Nia",
    "Owen", "Piper", "Quinn", "Rachel", "Simon",
    "Talia", "Uriel", "Violet", "Wyatt", "Ximena",
    "Yasmine", "Zachary", "Freya", "Gabriel", "Harper",
    "Isla", "Jack", "Kira", "Liam", "Maya",
    "Noah", "Olivia", "Peter", "Quinn", "Rachel",
    "Simon", "Talia", "Uriel", "Violet", "Wyatt",
    "Ximena", "Yasmine", "Zachary", "Finn", "Gemma",
    "Henry", "Ivy", "Jasper", "Keira", "Leo",
    "Mia", "Nolan", "Ophelia", "Patrick", "Quinn",
    "Rose", "Sebastian", "Thea", "Ulyana", "Vincent",
    "Willa", "Xavier", "Yvonne", "Zephyr", "Felix",
    "Giselle", "Hugo", "Ingrid", "Jonah", "Zoe"
};

// Define an array of person surnames
const vector<string> Surnames
{
    "Smith", "Johnson", "Williams", "Jones", "Brown",
    "Davis", "Miller", "Wilson", "Moore", "Taylor",
    "Anderson", "Thomas", "Jackson", "White", "Harris",
    "Martin", "Thompson", "Garcia", "Martinez", "Robinson",
    "Clark", "Rodriguez", "Lewis", "Lee", "Walker",
    "Hall", "Allen", "Young", "Hernandez", "King",
    "Wright", "Lopez", "Hill", "Scott", "Green",
    "Adams", "Baker", "Carter", "Cook", "Cooper",
    "Diaz", "Edwards", "Evans", "Flores", "Gonzalez",
    "Gray", "Hall", "Harris", "Hughes", "Jackson",
    "James", "Jenkins", "Johnson", "Jones", "Kelly",
    "Lee", "Lewis", "Long", "Lopez", "Martin",
    "Martinez", "Miller", "Mitchell", "Moore", "Morgan",
    "Morris", "Murphy", "Nelson", "Parker", "Perez",
    "Perry", "Powell", "Price", "Reed", "Roberts",
    "Robinson", "Rodriguez", "Rogers", "Ross", "Russell",
    "Sanchez", "Sanders", "Scott", "Smith", "Stewart",
    "Taylor", "Thomas", "Thompson", "Torres", "Turner",
    "Walker", "Ward", "Washington", "Watson", "White",
    "Williams", "Wilson", "Wood", "Wright", "Young"
};

const vector<string> bookPublishers
{
    "Stardust Press",
    "Quantum Quill Publishing",
    "Cosmic Chronicles Books",
    "Wanderlust Wordsmiths",
    "Enchanted Inkwell Publishers",
    "Time-Traveler's Tome",
    "Nebula Novelties",
    "Zephyr Zines",
    "Galactic Grimoires",
    "Whimsical Writings",
    "Astral Almanac Press",
    "Ethereal Editions",
    "Dreamweaver Publications",
    "Warp Drive Writers",
    "Celestial Cartography Books",
    "Surreal Sagas Publishing",
    "Stellar Storytellers",
    "Parallel Plotlines Press",
    "Quirky Quokka Quills",
    "Zigzagging Zeppelin Books",
    "Cosmic Cupcake Publishing",
    "Enigma Enterprises",
    "Zany Zebra Books",
    "Wisteria Way Words",
    "Peculiar Penguin Press",
    "Whispering Willow Writers",
    "Quixotic Quasar Publications",
    "Baffling Banana Books",
    "Zesty Zucchini Press",
    "Curious Cactus Publishing"
};

// Define an array of fictional book titles
// (https://johndabell.com/2021/06/21/pun-names-and-book-titles/ with additions)
const vector<string> bookTitles
{
    "A History of Welsh Comedians",
    "Advantageous",
    "Am I Bothered?",
    "American Breakfast",
    "Pancakes",
    "Are You Dancing?",
    "Art and Culture",
    "Blushing",
    "Bricklaying",
    "Bullriding",
    "Carbuncles",
    "Carpet Fitting",
    "Clothing",
    "Cloudburst",
    "Coffee Maker",
    "Coffees",
    "Common Cold Symptoms",
    "Constipation",
    "Continental Sausages",
    "Cooking Pasta",
    "Crime & Punishment",
    "Crumbs in My Cuppa",
    "Daddy Are We There Yet?",
    "Dublin",
    "Danger",
    "Deception",
    "Different",
    "Dentistry",
    "Diplomatic Mission",
    "Dog’s Dinner",
    "Electrical Wiring Made Easy",
    "Exploring other Galaxies",
    "Favourite Pizza Toppings",
    "Forthright",
    "French Cookery",
    "French Windows",
    "Geology",
    "Gibs",
    "Guardian",
    "Guardian of the Pizza",
    "Hair Today, Gone Tomorrow",
    "Heartbeat",
    "He Don't Love Me No More",
    "Horrendous",
    "Hunter",
    "Hot Dog",
    "Human",
    "Humanoids",
    "How can I Help?",
    "I Didn’t Do It!",
    "I Won!",
    "I’m Fine",
    "Insurance",
    "Islands",
    "It’s A Fake",
    "Keeping Scores",
    "Knighthood",
    "Large Snakes",
    "Leaflet Designs",
    "Lewis",
    "Leather Preparation For Beginners",
    "Lexicon",
    "Living on a Budget",
    "Losing a Budget",
    "Lumberjack",
    "Lucky",
    "Magnificent",
    "Magnification",
    "Magnitude",
    "Make Your Own Honey",
    "Mensa",
    "Morning",
    "Money Management",
    "Mosquito Bites",
    "Mosquerel",
    "My Worst Journey",
    "No Longer Required",
    "No Morning",
    "Not Too Hot, Not Too Cold",
    "Off the Beaten Track",
    "Office Software",
    "Optician’s Guide",
    "Outgoing Personality",
    "Outstanding",
    "Picnicking",
    "Picture",
    "Police Matters",
    "Pub Crawl",
    "Public City",
    "Pull Yourself Together",
    "Punctuality",
    "Punctuation",
    "Punctual",
    "Rowing The Pacific",
    "Rock",
    "Rocked Paper",
    "Rushing",
    "Rushed Paper",
    "School Sports",
    "Seaside Amusements",
    "Season",
    "Seasoned Amusements",
    "Shellfire",
    "Shockwave",
    "Sore Joints",
    "Stand-up Comedians",
    "Stealing Money",
    "Stone Age",
    "Stop Arguing",
    "Surprise!",
    "Survey",
    "Surveying Paper",
    "Suspended",
    "Suspense",
    "The Apiarist",
    "The Amusy",
    "Thirst Quencher",
    "Thorn",
    "Truancy",
    "Try Harder",
    "Voice Amplification",
    "Voice Bursts",
    "Without Warning",
    "Your Future"
};