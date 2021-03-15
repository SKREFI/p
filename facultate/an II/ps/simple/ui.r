library(shiny)

shinyUI(
  pageWithSidebar(
    headerPanel("Proiect PS: Chaos Game"),
      sidebarPanel(
        numericInput("N", "Number to visualize:", 2*3*3*7),
        radioButtons("colour", "Colours?", list("Yes" = 'yes', "No" = 'no')),
        radioButtons("segments", "Segments?", list("Yes" = 'yes', "No" = 'no')),
        sliderInput("direction", "Orientation:", min = -360, max = 360, value = 0)
      ),
      
      # Show a plot of the generated distribution
      mainPanel(
        h3(textOutput("caption")),
        plotOutput("visuPlot")
      )
  )
)