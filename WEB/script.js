const database = firebase.database()

var velocidadh4 = document.getElementById("velocidad");

const velocidadref = database.ref("velocidad");
velocidadref.on("value", (snapshot) => {
    const velocidad = snapshot.val();
    
    velocidadh4.innerHTML = velocidad;
})