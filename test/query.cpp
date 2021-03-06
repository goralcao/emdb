#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "query.h"
#include "emdb.h"
#include "storage/memory.h"


#include "test.h"


uint8_t test_compare_string ( ) {
  // equals
  uint8_t *text1 = (uint8_t *) "hello";
  uint8_t *text2 = (uint8_t *) "foo";

  check(compare_string(text1, text1, query_equals) == 1, "same text is considered equal");
  check(compare_string(text1, text2, query_equals) == 0, "different text is not considered equal");
  check(compare_string(text1, text1, query_gt) == 0, "equal text is not considered gt");
  check(compare_string(text1, text2, query_gt) == 1, "gt text is considered gt");
  check(compare_string(text2, text1, query_gt) == 0, "lt text is not considered gt");
  check(compare_string(text1, text1, query_lt) == 0, "equal text is not considered lt");
  check(compare_string(text2, text1, query_lt) == 1, "lt text is considered lt");
  check(compare_string(text1, text2, query_lt) == 0, "gt text is not considered lt");
  check(compare_string(text1, text1, query_gte) == 1, "same text is considered gte");
  check(compare_string(text1, text2, query_gte) == 1, "gt text is considered gte");
  check(compare_string(text1, text1, query_lte) == 1, "same text is considered lte");
  check(compare_string(text2, text1, query_lte) == 1, "lt text is considered lte");

  check(compare_string_between((uint8_t *) "goo", text2, text1) == 1, "between returns true when between");
  check(compare_string_between(text2, text2, text1) == 1, "between returns true when gte");
  check(compare_string_between(text1, text2, text1) == 1, "between returns true when lte");
  check(compare_string_between((uint8_t *) "ho", text2, text1) == 0, "between returns false when gt");
  check(compare_string_between((uint8_t *) "fa", text2, text1) == 0, "between returns false when lt");

  done();
}

uint8_t test_compare_int ( ) {
  uint16_t i1 = 10;
  uint16_t i2 = 20;

  check(compare_int(i1, i1, query_equals) == 1, "same integer is considered equal");
  check(compare_int(i1, i2, query_equals) == 0, "different integer is not considered equal");
  check(compare_int(i1, i1, query_gt) == 0, "equal integer is not considered gt");
  check(compare_int(i2, i1, query_gt) == 1, "gt integer is considered gt");
  check(compare_int(i1, i2, query_gt) == 0, "lt integer is not considered gt");
  check(compare_int(i1, i1, query_lt) == 0, "equal integer is not considered lt");
  check(compare_int(i1, i2, query_lt) == 1, "lt integer is considered lt");
  check(compare_int(i2, i1, query_lt) == 0, "gt integer is not considered lt");
  check(compare_int(i2, i1, query_gte) == 1, "gt integer is considered gte");
  check(compare_int(i1, i2, query_gte) == 0, "lt integer is not considered gte");
  check(compare_int(i1, i1, query_gte) == 1, "equal integer is considered gte");
  check(compare_int(i1, i1, query_lte) == 1, "equal integer is considered lte");
  check(compare_int(i1, i2, query_lte) == 1, "lt integer is considered lte");
  check(compare_int(i2, i1, query_lte) == 0, "gt integer is not considered lte");

  check(compare_int_between(15, i2, i1) == 1, "between returns true when between");
  check(compare_int_between(20, i2, i1) == 1, "between returns true when gte");
  check(compare_int_between(10, i2, i1) == 1, "between returns true when lte");
  check(compare_int_between(21, i2, i1) == 0, "between returns false when gt");
  check(compare_int_between(9, i2, i1) == 0, "between returns false when lt");

  check(compare_int_between(15, i1, i2) == 1, "between returns true when between reversed");
  check(compare_int_between(20, i1, i2) == 1, "between returns true when gte reversed");
  check(compare_int_between(10, i1, i2) == 1, "between returns true when lte reversed");
  check(compare_int_between(21, i1, i2) == 0, "between returns false when gt reversed");
  check(compare_int_between(9, i1, i2) == 0, "between returns false when lt reversed");

  done();
}

uint8_t test_compare_float ( ) {
  float f1 = 1.0;
  float f2 = 2.0;

  check(compare_float(f1, f1, query_equals) == 1, "same float is considered equal");
  check(compare_float(f1, f2, query_equals) == 0, "different float is not considered equal");
  check(compare_float(f1, f1, query_gt) == 0, "equal float is not considered gt");
  check(compare_float(f2, f1, query_gt) == 1, "gt float is considered gt");
  check(compare_float(f1, f2, query_gt) == 0, "lt float is not considered gt");
  check(compare_float(f1, f1, query_lt) == 0, "equal float is not considered lt");
  check(compare_float(f1, f2, query_lt) == 1, "lt float is considered lt");
  check(compare_float(f2, f1, query_lt) == 0, "gt float is not considered lt");
  check(compare_float(f2, f1, query_gte) == 1, "gt float is considered gte");
  check(compare_float(f1, f2, query_gte) == 0, "lt float is not considered gte");
  check(compare_float(f1, f1, query_gte) == 1, "equal float is considered gte");
  check(compare_float(f1, f1, query_lte) == 1, "equal float is considered lte");
  check(compare_float(f1, f2, query_lte) == 1, "lt float is considered lte");
  check(compare_float(f2, f1, query_lte) == 0, "gt float is not considered lte");

  check(compare_float_between(1.5, f2, f1) == 1, "between returns true when between");
  check(compare_float_between(2.0, f2, f1) == 1, "between returns true when gte");
  check(compare_float_between(1.0, f2, f1) == 1, "between returns true when lte");
  check(compare_float_between(2.1, f2, f1) == 0, "between returns false when gt");
  check(compare_float_between(0.9, f2, f1) == 0, "between returns false when lt");

  check(compare_float_between(1.5, f1, f2) == 1, "between returns true when between reversed");
  check(compare_float_between(2.0, f1, f2) == 1, "between returns true when gte reversed");
  check(compare_float_between(1.0, f1, f2) == 1, "between returns true when lte reversed");
  check(compare_float_between(2.1, f1, f2) == 0, "between returns false when gt reversed");
  check(compare_float_between(0.9, f1, f2) == 0, "between returns false when lt reversed");

  done();
}

uint8_t test_and_list ( ) {
  uint8_t *list1[6] = {
    (uint8_t *) "one",
    (uint8_t *) "two",
    (uint8_t *) "three",
    (uint8_t *) "four",
    (uint8_t *) "five",
    (uint8_t *) "six"
  };

  uint8_t *list2[4] = {
    (uint8_t *) "one",
    (uint8_t *) "two",
    (uint8_t *) "three"
  };

  uint16_t len = 0, i;
  uint8_t **results;

  results = and_list(list1, list2, 6, 3);

  for (i = 0; i < 5; i++) {
    if (results[i] == NULL) {
      len = i;
      break;
    }
  }

  check(len == 3, "and results have a length of 3");
  check((strcmp((char *) results[0], "one") == 0), "first result is correct");
  check((strcmp((char *) results[1], "two") == 0), "second result is correct");
  check((strcmp((char *) results[2], "three") == 0), "third result is correct");

  free(results);

  done();
}

uint8_t test_or_list ( ) {
  uint8_t *list1[6] = {
    (uint8_t *) "one",
    (uint8_t *) "two",
    (uint8_t *) "three",
    (uint8_t *) "four",
    (uint8_t *) "five",
    (uint8_t *) "six"
  };

  uint8_t *list2[4] = {
    (uint8_t *) "one",
    (uint8_t *) "two",
    (uint8_t *) "three"
  };

  uint8_t *list3[4] = {
    (uint8_t *) "seven",
    (uint8_t *) "eight",
    (uint8_t *) "nine"
  };

  uint16_t len = 0, i;
  uint8_t **results;

  results = or_list(list1, list2, 6, 3);

  for (i = 0; i < 10; i++) {
    if (results[i] == NULL) {
      len = i;
      break;
    }
  }

  check(len == 6, "and results have a length of 6");
  check((strcmp((char *) results[0], "one") == 0), "first result is correct");
  check((strcmp((char *) results[1], "two") == 0), "second result is correct");
  check((strcmp((char *) results[2], "three") == 0), "third result is correct");
  check((strcmp((char *) results[3], "four") == 0), "fourth result is correct");
  check((strcmp((char *) results[4], "five") == 0), "fifth result is correct");
  check((strcmp((char *) results[5], "six") == 0), "sixth result is correct");

  free(results);

  results = or_list(list1, list3, 6, 3);

  for (i = 0; i < 10; i++) {
    if (results[i] == NULL) {
      len = i;
      break;
    }
  }

  check(len == 9, "and results have a length of 9");
  check((strcmp((char *) results[0], "one") == 0), "first result is correct");
  check((strcmp((char *) results[1], "two") == 0), "second result is correct");
  check((strcmp((char *) results[2], "three") == 0), "third result is correct");
  check((strcmp((char *) results[3], "four") == 0), "fourth result is correct");
  check((strcmp((char *) results[4], "five") == 0), "fifth result is correct");
  check((strcmp((char *) results[5], "six") == 0), "sixth result is correct");
  check((strcmp((char *) results[6], "seven") == 0), "seventh result is correct");
  check((strcmp((char *) results[7], "eight") == 0), "eighth result is correct");
  check((strcmp((char *) results[8], "nine") == 0), "nineth result is correct");

  free(results);

  done();
}

// holds the results of a query in an accessible place in the local context
static QueryResults *query_results = NULL;

// simply set the query results to whatever was returned
static void query_callback (QueryResults *res) {
  query_results = res;
}

uint8_t test_simple_query ( ) {
  Where *where = (Where *) malloc(sizeof(Where));
  EMDB *db;
  uint8_t ret;
  Storage *store = getMemoryStorage();

  uint8_t *row1 = (uint8_t *) "{\"foo\":\"bar\"}";
  uint8_t *row2 = (uint8_t *) "{\"bar\":\"baz\"}";

  db = emdb_create_db(store, NULL);

  check(db != NULL, "database is created");

  ret = emdb_write(db, (uint8_t *) "foo", row1, strlen((char *) row1) + 1);
  check(ret == 1, "write is successful");
  ret = emdb_write(db, (uint8_t *) "bar", row2, strlen((char *) row2) + 1);
  check(ret == 1, "write is successful");

  // where clause - foo == bar
  where->type = query_equals;
  where->key = (uint8_t *) "foo";
  where->value.as_char = (uint8_t *) "bar";
  where->value_type = string;
  where->query_not = 0;

  emdb_query_db(db, where, query_callback);

  check((query_results != NULL), "query results are not null");
  check((query_results->count == 1), "return count is 1");

  free(where);
  emdb_free_results(query_results);
  emdb_destroy_db(db);

  done();
}
