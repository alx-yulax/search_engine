# Поисковый движок "SkillboxSE"

- Индексирует в отдельных потоках каждый файл содержащий текст;
- Осуществляет поиск по запросам из файла requests.json;
- Записывает результат поиска в файл answers.json в отсортированном виде;

##Примеры файлов
###config.json - файл конфигурационных данных
    {
      "config": {
        "name": "SkillboxSE",
        "version": "0.1",
        "max_responses": 5
      },
      "files": [
        "../resources/file001.txt",
        "../resources/file002.txt",
        "../resources/file003.txt",
    	"../resources/file004.txt",
    	"../resources/file005.txt",
    	"../resources/file006.txt",
    	"../resources/file007.txt",
    	"../resources/file008.txt",
    	"../resources/file009.txt",
    	"../resources/file010.txt",
    	"../resources/file011.txt",
    	"../resources/file012.txt",
    	"../resources/file013.txt",
    	"../resources/file014.txt",
    	"../resources/file015.txt",
    	"../resources/file016.txt",
    	"../resources/file017.txt",
    	"../resources/file018.txt",
    	"../resources/file019.txt",
    	"../resources/file020.txt",
    	"../resources/file021.txt",
        "../resources/file022.txt"
      ]
    }
- config — общая информация;
- name — поле с названием поискового движка;
- version — поле с номером версии поискового движка;
- max_responses — поле, определяющее максимальное количество ответов на
один запрос;
- files содержит пути к файлам, по которым необходимо осуществлять поиск.
Внутри списка files лежат пути к файлам.

###requests.json - файл с запросами
    {
      "requests": [
        "moscow is the capital of russia",
    	"moscow is",
    	"ttrttrre"
      ]
    }
- requests состоит из списка запросов, которые необходимо обработать
поисковым движком. Поле содержит не более 1000 запросов, каждый из
которых включает от одного до десяти слов.
- <содержимое запроса>(“moscow is”) — поисковый запрос, набор слов,
разделённых одним или несколькими пробелами. По ним необходимо
осуществить поиск. Все слова состоят из строчных латинских букв.

###answers.json - файл ответов на запросы
    {
      "answers": {
        "request001": {
          "relevance": [
            {
              "docid": 7,
              "rank": 1.0
            },
            {
              "docid": 14,
              "rank": 1.0
            },
            {
              "docid": 0,
              "rank": 0.6
            },
            {
              "docid": 1,
              "rank": 0.6
            },
            {
              "docid": 2,
              "rank": 0.6
            }
          ],
          "result": true
        },
        "request002": {
          "relevance": [
            {
              "docid": 7,
              "rank": 1.0
            },
            {
              "docid": 0,
              "rank": 0.5
            },
            {
              "docid": 1,
              "rank": 0.5
            },
            {
              "docid": 2,
              "rank": 0.5
            },
            {
              "docid": 3,
              "rank": 0.5
            }
          ],
          "result": true
        },
        "request003": {
          "result": false
        }
      }
    }

- answers — базовое поле в этом файле, которое содержит ответы на запросы;
- request001 … 003 — идентификатор запроса, по которому сформирован ответ;
- result – результат поиска запроса;
- relevance включается в файл answers.json, если на этот запрос удалось найти
более одного документа;
- <Идентификатор документа>("docid") — идентификатор документа, в котором
найден ответ на запрос;
- <ранг ответа>(“rank”) — ранг или поисковый рейтинг. Это число показывает,
насколько документ подходит для заданного запроса. В ответе id документов
располагаются в порядке уменьшения поискового рейтинга;
