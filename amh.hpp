class AMouseHandler : public IMouseHandler
{
   public:
      AmouseHandler(CWndPlayerCoordinate* frame);

   protected:
      virtual Boolean 
         mouseClicked(IMouseClickEvent &event),
         motion( IEvent &evt ),
         mousePointerChange(IMouseClickEvent &event);

   private:
      CWndPlayerCoordinate* frame;
} ;