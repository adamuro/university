# Brak drugiej części zadania o temperaturach

import matplotlib.pyplot as plt
import pandas as pd
import requests

COUNTRY_CODE = 'POL'

def records_dates(records):
  return records['month'].apply(str) + '/' + records['day'].apply(str) + '/' + records['year'].apply(str) 

with open('covid_data.csv', 'wb') as data:
  r = requests.get("https://opendata.ecdc.europa.eu/covid19/nationalcasedeath_eueea_daily_ei/csv/")
  data.write(r.content)

records = pd.read_csv('data.csv')
polish_records = records.loc[records['countryterritoryCode'] == COUNTRY_CODE]
warm_season_records = polish_records.loc[(5 < records['month']) & (records['month'] < 10)]
cold_season_records = polish_records.loc[(3 < records['month']) & (records['month'] < 6) ]

warm_season_records['date'] = pd.to_datetime(records_dates(warm_season_records))
cold_season_records['date'] = pd.to_datetime(records_dates(cold_season_records))

fig, ax = plt.subplots()

warm_season_records.plot(x='date', y='cases', ax=ax)
fig.suptitle('New COVID-19 cases during warm season in Poland')
fig.savefig('warm.png')

ax.cla()

cold_season_records.plot(x='date', y='cases', ax=ax)
fig.suptitle('New COVID-19 cases during cold season in Poland')
fig.savefig('cold.png')
