from credentials import creds

import requests

url = "https://spoonacular-recipe-food-nutrition-v1.p.rapidapi.com/recipes/complexSearch"

headers = {
    "X-RapidAPI-Key": creds['X-RapidAPI-Key'],
    "X-RapidAPI-Host": "spoonacular-recipe-food-nutrition-v1.p.rapidapi.com"
}

querystring = {
    "query": "pasta",
    "cuisine": "italian",
    "excludeCuisine": "greek",
    "diet": "vegetarian"
}

response = requests.request("GET", url, headers=headers, params=querystring)

print(response.text)

'''
{"results":
   [
      {
         "id":104974,
         "title":"Pasta Primavera",
         "image":"https://spoonacular.com/recipeImages/104974-312x231.jpg",
         "imageType":"jpg"
      },
      {
         "id":246727,
         "title":"Pasta e Fagioli",
         "image":"https://spoonacular.com/recipeImages/246727-312x231.jpg",
         "imageType":"jpg"
      },
      {
         "id":118762,
         "title":"Pasta Puttanesca",
         "image":"https://spoonacular.com/recipeImages/118762-312x231.jpg",
         "imageType":"jpg"
      },
      {
         "id":154062,
         "title":"Pasta à la Checca",
         "image":"https://spoonacular.com/recipeImages/154062-312x231.jpg",
         "imageType":"jpg"
      },
      {
         "id":138832,
         "title":"Pasta Cacio e Pepe",
         "image":"https://spoonacular.com/recipeImages/138832-312x231.jpg",
         "imageType":"jpg"
      },
      {
         "id":26885,
         "title":"Pasta Pomodoro My Way",
         "image":"https://spoonacular.com/recipeImages/26885-312x231.jpg",
         "imageType":"jpg"
      },
      {
         "id":856159,
         "title":
         "Pasta Primavera Stuffed In Bell Pepper",
         "image":"https://spoonacular.com/recipeImages/856159-312x231.jpg",
         "imageType":"jpg"
      },
      {
         "id":109882,
         "title":"Pasta Primavera With Cherry Tomato Sauce",
         "image":"https://spoonacular.com/recipeImages/109882-312x231.jpg",
         "imageType":"jpg"
      }
      ,
      {
         "id":516565,
         "title":"Pasta alla Formiana (or a healthified baked “ziti”)",
         "image":"https://spoonacular.com/recipeImages/516565-312x231.jpg",
         "imageType":"jpg"
      },
      {
         "id":486551,
         "title":"Pasta alla puttanesca {literally whore’s style pasta}",
         "image":"https://spoonacular.com/recipeImages/486551-312x231.jpg",
         "imageType":"jpg"
      }
   ],
   "offset":0,
   "number":10,
   "totalResults":135
}
'''
url2 = 'https://random-d.uk/api/v2/random'

response2 = requests.request("GET", url2)

print(response2.json())

'''
{
   'message': 'Powered by random-d.uk',
   'url': 'https://random-d.uk/api/243.jpg'
}
'''
