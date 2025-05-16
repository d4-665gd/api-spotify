export async function obtenerToken() {
    const res = await fetch("https://accounts.spotify.com/api/token", {
      method: "POST",
      headers: {
        Authorization:
          "Basic " +
          Buffer.from(
            process.env.SPOTIFY_CLIENT_ID + ":" + process.env.SPOTIFY_CLIENT_SECRET
          ).toString("base64"),
        "Content-Type": "application/x-www-form-urlencoded",
      },
      body: "grant_type=client_credentials",
    });
  
    const data = await res.json();
    return data.access_token;
  }
  
  export async function obtenerCanciones(token: string) {
    const res = await fetch(
      "https://api.spotify.com/v1/playlists/37i9dQZEVXbMDoHDwVN2tF", // Playlist Top 50
      {
        headers: {
          Authorization: "Bearer " + token,
        },
      }
    );
  
    const data = await res.json();
    return data.tracks.items.slice(0, 10).map((item: any) => ({
      id: item.track.id,
      nombre: item.track.name,
      artista: item.track.artists[0].name,
    }));
  }
  