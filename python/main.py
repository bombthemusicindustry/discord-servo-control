import asyncio
import discord
from discord.ext import commands
from utils import macro

bot = commands.AutoShardedBot(command_prefix=commands.when_mentioned_or("!"))


class Cogs:
    safe = [
      # enter cog paths here
    ]


# bot.remove_command("help")
#uncommment above if you have custom help command

for cog in Cogs.safe:
    bot.load_extension(cog)

#mama mia this is some spaghetti
@bot.event
async def on_command_error(ctx, error):
    if hasattr(ctx.command, 'on_error'):
        return

    ignored = commands.CommandNotFound

    error = getattr(error, 'original', error)

    if isinstance(error, ignored):
        return

    elif isinstance(error, commands.CommandOnCooldown):
        await ctx.send(embed=await macro.error(str(error)))

    elif isinstance(error, AssertionError):
        await ctx.send(embed=await macro.error(f"{str(error).replace('AssertionError: ', '')}"))

    elif isinstance(error, commands.DisabledCommand):
        await ctx.send(f'{ctx.command} has been disabled.')

    elif isinstance(error, commands.errors.MissingRequiredArgument):
        await ctx.send(embed=await macro.error(f"You forgot an argument!\n```{error}```"))
    else:
        await ctx.send(embed=await macro.error(f"{error}"))

@bot.event
async def on_ready():
  print("Ready! Make sure to run control.ioo to make this work!")
  print(f"Bot User: {bot.user}")

bot.run('token')
