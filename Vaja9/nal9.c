#include <bson/bson.h>
#include <mongoc/mongoc.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *doc1;
    bson_error_t error;
    bson_t *query;
    bson_oid_t oid;
    char *str;

    mongoc_init();

    client = mongoc_client_new("mongodb://localhost:27017/?appname=find-example");
    collection = mongoc_client_get_collection(client, "db", "table");
    query = bson_new();  // {} empty query
    cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);

    while (mongoc_cursor_next(cursor, &doc)) {
        str = bson_as_canonical_extended_json(doc, NULL);
        printf("%s\n", str);
        bson_free(str);
    }

    // ADD new document
    doc1 = bson_new();
    bson_oid_init(&oid, NULL);
    BSON_APPEND_OID(doc1, "_id", &oid);
    BSON_APPEND_UTF8(doc1, "hello", "world");

    if (!mongoc_collection_insert_one(collection, doc1, NULL, NULL, &error)) {
        fprintf(stderr, "%s\n", error.message);
    }
    bson_destroy(doc1);

    // REPEAT query

    cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
    while (mongoc_cursor_next(cursor, &doc)) {
        str = bson_as_canonical_extended_json(doc, NULL);
        printf("%s\n", str);
        bson_free(str);
    }

    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
    mongoc_collection_destroy(collection);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    return 0;
}