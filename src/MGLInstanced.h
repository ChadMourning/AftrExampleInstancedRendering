#include "Model.h"

namespace Aftr
{
   class MGLInstanced : public Model
   {
   public:
      static MGLInstanced* New(WO* parent, const std::string& model);
      virtual ~MGLInstanced();
      void render(const Camera& cam) override;
      virtual void onCreate(const std::string& model);
   protected:
      MGLInstanced(WO* parent);

   };
};