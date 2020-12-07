// part 1
// Count the number of valid passports - those that
// have all required fields. Treat cid as optional.
// In your batch file, how many passports are valid?

// part 2
// byr (Birth Year) - four digits; at least 1920 and at most 2002.
// iyr (Issue Year) - four digits; at least 2010 and at most 2020.
// eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
// hgt (Height) - a number followed by either cm or in:
//     If cm, the number must be at least 150 and at most 193.
//     If in, the number must be at least 59 and at most 76.
// hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
// ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
// pid (Passport ID) - a nine-digit number, including leading zeroes.
// cid (Country ID) - ignored, missing or not.
// Your job is to count the passports where all required fields are both
// present and valid according to the above rules.


const fs = require("fs");

fs.readFile("passports.txt", "utf-8", (error, data) => {
    const passports = data.split("\n\n");
    // excluding cid since it isnt necessary
    const fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"];

    function partOne() {
        // number of valid passports
        let valid = 0
        // executes for each element in passports
        passports.forEach(passport => {
            // if fields are included somewhere in each element
            if (fields.every((x) => passport.includes(x))) {
                valid++
            }
        });
        return valid;
    }

    console.log(`part 1: ${partOne()}`)

    function PartTwo() {
        // array of valid passports
        let valid_passports = [];
        let valid = 0

        // rules to validate
        const rules = [
            {key: "byr", validate: (v) => v >= 1920 && v <= 2002},
            {key: "iyr", validate: (v) => v >= 2010 && v <= 2020},
            {key: "eyr", validate: (v) => v >= 2020 && v <= 2030},
            {key: "hgt", validate: (v) => {
                const num = v.replace(/\D/g,'');
                return v.match(new RegExp('cm|in')) && (v.includes('cm') ? num >= 150 && num <= 193 : num >= 59 && num <= 76);
            }},
            {key: "hcl", validate: (v) => v.match(/^#[0-9A-F]{6}$/i)},
            {key: "ecl", validate: (v) => v.match(new RegExp(['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth'].join('|'), 'g'))},
            {key: "pid", validate: (v) => !isNaN(v) && v.split('').length === 9},
            {key: 'cid', validate: (v) =>  false}
        ]

        // for each passport
        passports.forEach(passport => {
            // number of valid passports
            let valid_each = 0
            // the fields to validate
            let passport_fields = passport.split(new RegExp(['\n', ' '].join('|'), 'g'));

            // for each field with a value after the :
            passport_fields.forEach(passport_fields => {
                const passport_values = passport_fields.split(":");
                // validate each value
                if (rules.filter(x => x.key === passport_values[0])[0].validate(passport_values[1])) {
                    valid_each++
                }
            });

            // if all of the fields in a passport are valid -> there are better ways to do this
            if (valid_each === 7) {
                valid++
            }
        });
        return valid;
    }
    console.log(`part 2: ${PartTwo()}`);
})