const ytdl = require('ytdl-core')
const yts = require('yt-search')

let search = "morro do dende"

yts(search, (err, res) => {
    if(!err){
        let video = res.videos[0]
        console.log(video)
        console.log(ytdl.validateURL(video.url))
        ytdl.getInfo(`${video.videoId}`, (err, info) => {
            console.log(info)
        })
    }
})