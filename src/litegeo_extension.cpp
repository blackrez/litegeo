#define DUCKDB_EXTENSION_MAIN

#include "litegeo_extension.hpp"
#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/common/string_util.hpp"
#include "duckdb/function/scalar_function.hpp"
#include "duckdb/main/extension_util.hpp"
#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>


namespace duckdb {

inline void LitegeoScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
    auto &name_vector = args.data[0];
    UnaryExecutor::Execute<string_t, string_t>(
	    name_vector, result, args.size(),
	    [&](string_t name) {
			return StringVector::AddString(result, "Litegeo "+name.GetString()+" 🐥");;
        });
}

static void LoadInternal(DatabaseInstance &instance) {
    // Register a scalar function
    auto litegeo_scalar_function = ScalarFunction("litegeo", {LogicalType::VARCHAR}, LogicalType::VARCHAR, LitegeoScalarFun);
    ExtensionUtil::RegisterFunction(instance, litegeo_scalar_function);

}

void LitegeoExtension::Load(DuckDB &db) {
	LoadInternal(*db.instance);
}
std::string LitegeoExtension::Name() {
	return "litegeo";
}

} // namespace duckdb

extern "C" {

DUCKDB_EXTENSION_API void litegeo_init(duckdb::DatabaseInstance &db) {
    duckdb::DuckDB db_wrapper(db);
    db_wrapper.LoadExtension<duckdb::LitegeoExtension>();
}

DUCKDB_EXTENSION_API const char *litegeo_version() {
	return duckdb::DuckDB::LibraryVersion();
}
}

#ifndef DUCKDB_EXTENSION_MAIN
#error DUCKDB_EXTENSION_MAIN not defined
#endif
