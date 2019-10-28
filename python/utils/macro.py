from discord import Color as C, Embed as E


class Macro:
    @staticmethod
    async def message(desc: str = None, title: str = None, color: C = C.blue()):
        return E(
            title=title,
            description=desc,
            color=color,
            type='rich'
        )

    @classmethod
    async def img(cls, url: str):
        message = await cls.message()
        message.set_image(url=url)
        return message

    @classmethod
    async def error(cls, desc: str):
        return await cls.message(desc=desc, color=C.red(), title=":octagonal_sign: Error! :octagonal_sign: ")


send = Macro.message
img = Macro.img
err = Macro.error
