from nba_api.stats.endpoints import (
    playercareerstats,
    playergamelog,
    leaguedashplayerstats,
    leaguedashteamstats,
    teamgamelogs
)
from nba_api.stats.static import players, teams
import json
from datetime import datetime
import time
import os
import pandas as pd

#         "Game": 8,
#         "Opponent": "GSW",
#         "Prev_5_Points": 32.2,
#         "Prev_5_FG%": 53.3,
#         "Prev_5_TS%":
#         "Prev_5_eFG%":
#         "Prev_5_USG%":
#         "Prev_5_PER":
#         "PPG_Vs_Opp":
#         "Opp_Def_Rating": 109.6,
#         "Is_Home": 0,
#         "Is_B2B":
#         "Over_Under": 28.5,
#         "Label": 1

"""
TODO: 
-use loops to get prev 5 game ppg, fg, ts, efg, usg, per(maybe)
-List each team id hardcoded with abbreviations to get team defensive rating
-use dates for back to back, is home away
-game numbers?
-use player career log to get ppg vs team previously
"""

# find deni's player profile
deni = [p for p in players.get_players() if p['full_name'] == 'Deni Avdija'][0]
deni_id = deni['id'] # get his id

gamelog = playergamelog.PlayerGameLog(player_id=deni_id, season='2025-26')
df = gamelog.get_data_frames()[0]


print(df.iloc[0][24]) # loop thru to find last 5 of each game

print(df[['GAME_DATE', 'Game_ID', 'MATCHUP', 'WL']].head())


# HARDCODE EVERY TEAM ID WITH ABBREVIATION
# team id
blazers = [t for t in teams.get_teams() if t['full_name'] == 'Portland Trail Blazers'][0]
team_id = blazers['id']

team_log = teamgamelogs.TeamGameLogs(
    team_id_nullable=team_id,
    season_nullable='2025-26',
    season_type_nullable='Regular Season'
)
dff = team_log.get_data_frames()[0]

dff['OPPONENT_ABBR'] = dff['MATCHUP'].apply(lambda x: x.split()[-1])


# print(dff['GAME_DATE'].iloc[7] > dff['GAME_DATE'].iloc[8]) # can compare dates

#print(dff[['MATCHUP']].head())

# get all player stats
# endpoint = leaguedashplayerstats.LeagueDashPlayerStats(season='2025-26')

# # get first data frame from player stats
# df = endpoint.get_data_frames()[0]

# # deni's stats
# deni_row = df[df['PLAYER_ID'] == deni_id].iloc[0]

# print(deni_row.to_string())

# ppg = deni_row['PTS'] / deni_row['GP']
# print("\nPPG: ", ppg)

# ts_pct = deni_row['PTS'] / (2 * (deni_row['FGA'] + 0.44 * deni_row['FTA']))
# print("\nTS%: ", ts_pct)

# get all team stast
team_stats = leaguedashteamstats.LeagueDashTeamStats(season='2025-26', measure_type_detailed_defense='Advanced',).get_data_frames()[0]

print(team_stats.columns)

# # blazers stats
# blazers_stats = team_stats[team_stats['TEAM_NAME'] == 'Portland Trail Blazers'].iloc[0]

# usg = (100 * ((deni_row['FGA'] + 0.44 * deni_row['FTA'] + deni_row['TOV']) * (blazers_stats['MIN'])) 
# / (deni_row['MIN'] * (blazers_stats['FGA'] + 0.44 * blazers_stats['FTA'] + blazers_stats['TOV'])))

# print("\nUSG%: ", usg)

# print(blazers_stats.to_string())

# merge player stats into dataframe, linear regression training using scikitlearn



# # Filter for Portland Trail Blazers
# portland_row = team_stats[team_stats['TEAM_NAME'] == 'Portland Trail Blazers'].iloc[0]

# # Combine into one summary
# summary = {
#     'Player': deni_row['PLAYER_NAME'],
#     'Team': portland_row['TEAM_NAME'],
#     'PPG': deni_row['PTS'],
#     'FG%': deni_row['FG_PCT'],
#     # 'TS%': deni_row['TS_PCT'],
#     # 'Usage Rate': deni_row['USG_PCT'],
#     # 'Minutes': deni_row['MIN'],
#     # 'PIE (PER proxy)': deni_row['PLAYER_IMPACT_EST'],
#     # 'Team Pace': portland_row['PACE'],
#     # 'Team Def Rating': portland_row['DEF_RATING'],
# }

# print(pd.Series(summary))


# def display_live_games():
#     # Fetch the current scoreboard data
#     board = scoreboard.ScoreBoard()
#     games = board.games.get_dict()

#     os.system('cls' if os.name == 'nt' else 'clear')

#     # Check if there are any live games
#     if not games:
#         print("No live NBA games right now.")
#         return

#     print(f"\Live NBA Games {datetime.now().strftime('%B %d, %Y %I:%M %p')}\n")
 
#     for game in games:
#         home_team = game['homeTeam']['teamName']
#         away_team = game['awayTeam']['teamName']
#         home_score = game['homeTeam']['score']
#         away_score = game['awayTeam']['score']
#         game_status = game['gameStatusText']
      
#         print(f"{away_team} ({away_score}) @ {home_team} ({home_score}) - {game_status}")

# # Run the function
# def main():
#     while True:
#         display_live_games()
#         time.sleep(10)  # refresh every 60 seconds
#         print("\nUpdating...\n")

# if __name__ == "__main__":
#     main()


