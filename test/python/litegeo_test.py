import duckdb
import os
import pytest

# Get a fresh connection to DuckDB with the litegeo extension binary loaded
@pytest.fixture
def duckdb_conn():
    extension_binary = os.getenv('LITEGEO_EXTENSION_BINARY_PATH')
    if (extension_binary == ''):
        raise Exception('Please make sure the `LITEGEO_EXTENSION_BINARY_PATH` is set to run the python tests')
    conn = duckdb.connect('', config={'allow_unsigned_extensions': 'true'})
    conn.execute(f"load '{extension_binary}'")
    return conn

def test_litegeo(duckdb_conn):
    duckdb_conn.execute("SELECT litegeo('Sam') as value;");
    res = duckdb_conn.fetchall()
    assert res[0][0] == "Litegeo Sam 🐥"

def test_litegeo_openssl_version_test(duckdb_conn):
    duckdb_conn.execute("SELECT litegeo_openssl_version('Michael');");
    res = duckdb_conn.fetchall()
    assert res[0][0][0:51] == "Litegeo Michael, my linked OpenSSL version is OpenSSL"
