var duckdb = require('../../duckdb/tools/nodejs');
var assert = require('assert');

describe(`litegeo extension`, () => {
    let db;
    let conn;
    before((done) => {
        db = new duckdb.Database(':memory:', {"allow_unsigned_extensions":"true"});
        conn = new duckdb.Connection(db);
        conn.exec(`LOAD '${process.env.LITEGEO_EXTENSION_BINARY_PATH}';`, function (err) {
            if (err) throw err;
            done();
        });
    });

    it('litegeo function should return expected string', function (done) {
        db.all("SELECT litegeo('Sam') as value;", function (err, res) {
            if (err) throw err;
            assert.deepEqual(res, [{value: "Litegeo Sam 🐥"}]);
            done();
        });
    });

    it('litegeo_openssl_version function should return expected string', function (done) {
        db.all("SELECT litegeo_openssl_version('Michael') as value;", function (err, res) {
            if (err) throw err;
            assert(res[0].value.startsWith('Litegeo Michael, my linked OpenSSL version is OpenSSL'));
            done();
        });
    });
});