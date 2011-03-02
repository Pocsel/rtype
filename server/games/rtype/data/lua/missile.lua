function rtypeMissile(itemId, spawnTime, curTime, elapsedTime)
    if speedX > 70 then
        if speedY > 50 then
            framePos = 5 -- down right
        elseif speedY < -50 then
            framePos = 3 -- up right
        else
            framePos = 4 -- right
        end
    elseif speedX < -70 then
        if speedY > 50 then
            framePos = 7 -- down left
        elseif speedY < -50 then
            framePos = 1 -- up left
        else
            framePos = 0 -- left
        end
    else
        if speedY > 0 then
            framePos = 6 -- down
        else
            framePos = 2 -- up
        end
    end
end

