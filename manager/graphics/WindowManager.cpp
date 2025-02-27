class WindowManager {
    public:
        static WindowManager* get();
    
        void init(SDL_Window* window);
        void loadTexture(const std::string& key, const std::string& path);
        void renderTexture(const std::string& key, int x, int y, int w, int h);
        void cleanUp();
        
    
    private:
        static WindowManager _am;
        WindowManager() : _window(nullptr), _renderer(nullptr) {}
        ~WindowManager() { cleanUp(); }
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        
    
    };