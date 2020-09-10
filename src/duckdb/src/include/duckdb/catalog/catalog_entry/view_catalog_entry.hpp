//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/catalog/catalog_entry/view_catalog_entry.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/catalog/standard_entry.hpp"
#include "duckdb/parser/query_node.hpp"
#include "duckdb/common/types.hpp"
#include "duckdb/common/vector.hpp"

namespace duckdb {

class ColumnStatistics;
class DataTable;
struct CreateViewInfo;

//! A view catalog entry
class ViewCatalogEntry : public StandardEntry {
public:
	//! Create a real TableCatalogEntry and initialize storage for it
	ViewCatalogEntry(Catalog *catalog, SchemaCatalogEntry *schema, CreateViewInfo *info);

	//! The query of the view
	unique_ptr<QueryNode> query;
	//! The SQL query (if any)
	string sql;
	//! The set of aliases associated with the view
	vector<string> aliases;
	//! The returned types of the view
	vector<LogicalType> types;

public:
	//! Serialize the meta information of the ViewCatalogEntry a serializer
	virtual void Serialize(Serializer &serializer);
	//! Deserializes to a CreateTableInfo
	static unique_ptr<CreateViewInfo> Deserialize(Deserializer &source);

	string ToSQL() override;

private:
	void Initialize(CreateViewInfo *info);
};
} // namespace duckdb
