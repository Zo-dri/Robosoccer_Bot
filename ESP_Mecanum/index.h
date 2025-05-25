const char *HTML_CONTENT = R"=====(
  <!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <title>Dual Joystick Control</title>
    <style>
      body {
        display: flex;
        justify-content: space-around;
        align-items: center;
        height: 100vh;
        margin: 0;
        background: #111;
        color: white;
        font-family: sans-serif;
      }
      .joystick-container {
        width: 150px;
        height: 150px;
        position: relative;
        border: 2px solid #444;
        border-radius: 50%;
      }
      #status {
        position: absolute;
        bottom: 20px;
        left: 50%;
        transform: translateX(-50%);
        font-size: 18px;
      }
    </style>
  </head>
  <body>
    <div>
      <h2>Move</h2>
      <div id="joystick1" class="joystick-container"></div>
    </div>
    <div>
      <h2>Rotate</h2>
      <div id="joystick2" class="joystick-container"></div>
    </div>
    <div id="status">Connecting...</div>

    <script src="https://cdnjs.cloudflare.com/ajax/libs/nipplejs/0.9.0/nipplejs.min.js"></script>
    <script>
      const joystickOptions = {
        zone: null,
        mode: 'static',
        position: { left: '50%', top: '50%' },
        color: 'cyan',
        size: 200
      };

      let movement = { angle: 0, speed: 0 };
      let rotation = 0;

      function sendCommand() {
        fetch(`/move?angle=${movement.angle}&speed=${movement.speed}&rotation=${rotation}`)
          .then(res => res.text())
          .then(data => document.getElementById('status').textContent = data)
          .catch(err => console.error('Error:', err));
      }

      function createJoystick(containerId, onMove) {
        const options = { ...joystickOptions, zone: document.getElementById(containerId) };
        const manager = nipplejs.create(options);

        manager.on('move', (evt, data) => {
          if (data && data.angle) {
            onMove(data);
            sendCommand();
          }
        });

        manager.on('end', () => {
          if (containerId === 'joystick1') {
            movement.speed = 0;
          } else {
            rotation = 0;
          }
          sendCommand();
        });
      }

      createJoystick('joystick1', (data) => {
        movement.angle = Math.round(data.angle.degree);
        movement.speed = Math.round(data.distance);
      });

      createJoystick('joystick2', (data) => {
        let angle = data.angle.degree;
        // Assume angle 0 = up, 180 = down
        rotation = (angle > 180) ? -1 : 1;
        rotation *= Math.round(data.distance / 10); // Normalize
      });
    </script>
  </body>
  </html>
)=====";