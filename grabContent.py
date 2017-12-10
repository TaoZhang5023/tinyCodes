import urllib.request
from bs4 import BeautifulSoup
import re
import csv
links = set()
quote_page = "http://freedomfoods.com.au/product-category/food-type/cereal-muesli/"
page = urllib.request.urlopen(quote_page)
soup = BeautifulSoup(page, "html.parser")
linkTags = soup.findAll('a',{"class": "product-images"})
with open("index.csv", "a", encoding='utf-8') as csv_file:
	writer = csv.writer(csv_file)
	for tag in linkTags:
		links.add(tag.get('href'))
	for link in links:
		print(link)
		page = urllib.request.urlopen(link)
		soup = BeautifulSoup(page, "html.parser")
		title = soup.find('h2',{"class": "product_title"})
		title = title.text
		print(title)
		writer.writerow([title,link])


		suggestion = soup.find('p',string=re.compile('^\^'))
		suggestion = suggestion.text
		print(suggestion)
		writer.writerow([suggestion])

		ingredients = soup.find('div',{"id": "tab-ingredient-list"})
		ingredients = ingredients.findAll('p')
		ingredientInfo=""
		for ingredient in ingredients:
			ingredientInfo += str(ingredient.text)
		print(ingredientInfo)
		writer.writerow([ingredientInfo])


		nutriTab = soup.find('div',{"id":"tab-nutritional-info"})
		searchSize = nutriTab.find('td', string=re.compile('[S,s]erving [S,s]ize:'))
		if(searchSize is None):
			searchSize = nutriTab.find('p')
		servingSize = searchSize.text
		print(servingSize)
		servingSize = re.compile("[S,s]erving [S,s]ize:").split(servingSize)[1]
		print(servingSize)
		writer.writerow(["Serving size: ", servingSize])


		nutriTable = nutriTab.find('table', recursive=False)
		nutriInfos = nutriTable.findAll('tr')
		if(nutriTable.find('table') is not None):
			nutriInfos = nutriTable.find('table').findAll('tr')
		for nutriInfo in nutriInfos:
			info100 = ""
			tds = nutriInfo.findAll("td")
			if len(tds) >= 3:
				info100 = info100 + str(tds[0].text) + ", " + str(tds[2].text)
				print(info100)
				writer.writerow([tds[0].text, tds[2].text])
		writer.writerow("")




# link = "http://freedomfoods.com.au/product/xo-crunch/"
# print(link)
# page = urllib.request.urlopen(link)
# soup = BeautifulSoup(page, "html.parser")
# title = soup.find('h2',{"class": "product_title"})
# title = title.text
# print(title)
# suggestion = soup.find('p',string=re.compile('^\^'))
# suggestion = suggestion.text
# print(suggestion)
# ingredients = soup.find('div',{"id": "tab-ingredient-list"})
# ingredients = ingredients.findAll('p')
# ingredientInfo=""
# for ingredient in ingredients:
# 	ingredientInfo += str(ingredient.text)
# print(ingredientInfo)
# nutriTab = soup.find('div',{"id":"tab-nutritional-info"})
# searchSize = nutriTab.find('td', string=re.compile('[S,s]erving [S,s]ize:'))
# if(searchSize is None):
# 	searchSize = nutriTab.find('p')

# servingSize = searchSize.text
# print(servingSize)
# servingSize = re.compile("[S,s]erving [S,s]ize:").split(servingSize)[1]
# print(servingSize)
# nutriTable = nutriTab.find('table', recursive=False)
# nutriInfos = nutriTable.findAll('tr')
# if(nutriTable.find('table') is not None):
# 	nutriInfos = nutriTable.find('table').findAll('tr')
# for nutriInfo in nutriInfos:
# 	info100 = ""
# 	print(nutriInfo)
# 	tds = nutriInfo.findAll("td")
# 	if len(tds) >= 3:
# 		info100 = info100 + str(tds[0].text) + ", " + str(tds[2].text)
# 		print(info100)



	# trs = table.findAll("tr")
	# servingSize = trs[1].find('td').text
	# servingSize = servingSize.split("Serving Size:",1)[1]
	# print(servingSize)
	# nutriTable = trs[2].find('table')
	# nutriInfos = nutriTable.findAll('tr')
	# for nutriInfo in nutriInfos:
	# 	info100 = ""
	# 	for td in nutriInfo.findAll("td"):
	# 		info100 += str(td.text)
	# 	print(info100)


# name_box = soup.find("h1", attrs={"class": "name"})
# name = name_box.text.strip() # strip() is used to remove starting and trailing
# print(name)