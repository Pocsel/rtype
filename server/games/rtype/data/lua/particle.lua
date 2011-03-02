gl_particles = {}

function rtypeParticleCreate(itemId)
    gl_particles[itemId] = {}
    gl_particles[itemId]["spawnX"] = posX
    gl_particles[itemId]["spawnY"] = posY
    gl_particles[itemId]["amplitude"] = math.random() * 10 + 10
    gl_particles[itemId]["length"] = math.random() + 0.5
end

function rtypeParticle(itemId, spawnTime, curTime, elapsedTime)
    posX = posX - 3
    posY = math.sin(curTime * gl_particles[itemId]["length"]) * gl_particles[itemId]["amplitude"] + gl_particles[itemId]["spawnY"]
end

function rtypeParticleDelete(itemId)
    table.remove(gl_particles, itemId)
end

