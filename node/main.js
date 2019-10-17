const ytdl = require('ytdl-core')
const yts = require('yt-search')

let search = "morro do dende"

yts(search, async (err, res) => {
    if(!err){
        let video = res.videos[0]
        console.log(video)
        await ytdl.getInfo(`${video.videoId}`, (err, info) => {
            console.log(info.player_response.videoDetails.thumbnail.thumbnails.pop())
            console.log(info.author)
        })
    }
})