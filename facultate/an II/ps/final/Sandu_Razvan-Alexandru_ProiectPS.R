server <- shinyServer(function(input, output, session) {
  # in the place where we said that "it will exist a reactive <div> somewhere in the server, now we build it in here
  # we build it inside the server so that we can change the values in the server and so that it won't affect the whole application, only whatever is shared with it, in this case the generation of the points
  output$my.pts <- renderUI({
    input$shape
    sliderInput(
      "pts",
      "Number of points:",
      min = 1000,
      max = 50000,
      step = 1000,
      value = 1000,
      animate = animationOptions(interval = 200)
    )
  })
  
  # button from shinyBS that will help randomize 
  updateButton(
    session,
    inputId = "generate",
    style = "primary",
    size = "default",
    disabled = FALSE
  )
  
  # all.list is a reactive expression that will return the values either from tri.generate, or from pent.generate
  all.list <- reactive({
    if (input$shape == "tri") {
      #
      return(tri.generate(input$dist.tri * (input$generate > -1)))
    }
    if (input$shape == "pent") {
      return(pent.generate(input$dist.pent * (input$generate > -1)))
    }
  })
  
  # the renderPlot builds a responsive plot, the output will pass down what has been built to the server
  output$compPlot <- renderPlot({
    # we'll be able to work with the values from the functions inside a reactive plot, which means that any change will refresh the plot
    loc_index <- all.list()[[1]]
    # vertexes  <- all.list()[[2]]
    coords    <- all.list()[[3]]
    
    # Triunghi
    if (input$shape == "tri") {
      # mar represent the margin of the plot, a little space between all the other elements
      par(mar = c(0.5, 0.5, 0.5, 0.5))
      plot(
        0,
        0,
        # the limiting of the x and y max values, equivalent of limiting the canvas in our case
        xlim = c(0, 1),
        ylim = c(0, sqrt(3) / 2),
        # n stands for "no plotting", so they won't show the values on the x and y axes
        yaxt = "n",
        xaxt = "n",
        # no labels for the x & y axes
        xlab = "",
        ylab = ""
        # , bty = "n"
      )
    }
    
    # Pentagon
    if (input$shape == "pent") {
      c1 <- 0.25 * (sqrt(5) - 1)
      c2 <- 0.25 * (sqrt(5) + 1)
      s1 <- 0.25 * (sqrt(10 + 2 * sqrt(5)))
      s2 <- 0.25 * (sqrt(10 - 2 * sqrt(5)))
      
      (mar = c(0.5, 0.5, 0.5, 0.5))
      plot(
        0,
        0,
        xlim = c(-s1, s1),
        ylim = c(-c2, 1),
        col = 0,
        yaxt = "n",
        xaxt = "n",
        xlab = "",
        ylab = ""
        # , bty = "n"
      )
    }
    
    # stylizing the blue points, the generated ones
    points(
      coords[1:input$pts, 1],
      coords[1:input$pts, 2],
      pch = ".",
      cex = 2.5,
      col = "blue"
    )
    
    # stylizing the red points, the endpoints
    points(
      loc_index[, 2],
      loc_index[, 3],
      pch = 20,
      cex = 2,
      col = "red"
    )
  })
})

# shinyApp builds the whole responsive shiny app, which will take the 'ui' and 'server' values to work with
shinyApp(ui = ui, server = server)