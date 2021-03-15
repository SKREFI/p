library(shiny)
library(shinyBS)

shinyUI(fluidPage(
  tags$title("Proiect PS: Chaos Game"),
  h3("Proiect PS: Chaos Game"),
  fluidRow(
    column(4,
           wellPanel(
             selectizeInput('shape', h5(tags$b('Shape')), choices = list("Forme" = c(`Triunghi` = 'tri', `Pentagon` = 'pent')), selected = 'tri'),
             
             conditionalPanel(
               condition = "input.shape=='tri'",
               sliderInput("dist.tri", label = h5(tags$b("Ratie Distanta:")),
                           min = 0.01, max = .99, value = .50, step=.01),
               div("Ratia default este: 0.50",
                   style = "font-size: 9.5pt;color:teal",align="left")
             ),
             
             conditionalPanel(
               condition = "input.shape=='pent'",
               sliderInput("dist.pent", label = h5(tags$b("Ratie Distanta:")),
                           min = 0.01, max = .99, value = .63, step=.01),
               div("Ratia default 0.63", style = "font-size: 9.5pt;color:teal",align="left")
             ),
             br(),
             conditionalPanel(condition="input.tabselected==3",
                              div(uiOutput("my.pts"))
             ),
             br(),
             div(bsButton("gen", label="Randomize"),align="right")
           ) #sidebarPanel
    ), #column-4
    column(8,
           tabsetPanel(type = "tabs",id = "tabselected", tabPanel("Vizualizare",value=3,
                                fluidRow(
                                  column(12,
                                         div(
                                           div(
                                             plotOutput("compPlot"),style="width:500px",inline="TRUE"),align="center"),
                                         HTML("<hr style='height: 2px; color: #BDBDBD; background-color: #D9D9D9; border: none;'>")
                                         
                                  ), # column-12
                                  fluidRow(
                                    column(10, offset=1
                                    ) # column-10
                                  ) #fluidRow
                                ) #fluidRow
                       )  # close tabPanel-Complete
           )# tabsetPanel
    )# column-8
  ) # fluidRow
)# fluidPage
)# shinyUI
