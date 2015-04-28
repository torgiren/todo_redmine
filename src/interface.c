#include"interface.h"
#include"curl_redmine.h"
void print_issues()
{
    json_t *issues = curl_redmine_get_issues();
    size_t index;
    json_t *value;
    json_array_foreach(issues, index, value)
    {
        json_t *project, *author;
        project = json_object_get(value, "project");
        author = json_object_get(value, "author"); 
        printf("%d\t%s\t%s\t%s\t%s\n",
                (int)index,
                json_string_value(json_object_get(project,"name")),
                json_string_value(json_object_get(author,"name")),
                json_string_value(json_object_get(value,"subject")),
                json_string_value(json_object_get(value,"created_on"))
              );
    }
}
