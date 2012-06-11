// Load after jquery


api = {}

api._callbacks = [];

api._callback = function(id, arr) {
  console.log("callback " + id + " | " + arr);
  api._callbacks[id].apply(null, arr);
}

api._register_callback = function(callback) {
  api._callbacks.push(callback);
  return api._callbacks.length - 1;
}


$(function(){console.log("yo");window._api.callback.connect(api._callback);});

api.invokeRubySubprocess = function(args, callback) {
  return window._api.invokeRubySubprocess(args, api._register_callback(callback));
}

api.readThumbnail = window._api.readThumbnail;

api.exifTime = window._api.exifTime;

api.droppedFilesRecursive = window._api.droppedFilesRecursive;

api.makeDirectory = window._api.makeDirectory;

api.writeFile = window._api.writeFile;

api.readFile = window._api.readFile;

api.saveAsDialog = window._api.saveAsDialog;

api.setUndoMenu = window._api.setUndoMenu;

api.setRedoMenu = window._api.setRedoMenu;

api.getOpenedProjectPath = window._api.getOpenedProjectPath;

api.setOpenProjectMenu = window._api.setOpenProjectMenu;

api.setSaveMenu = window._api.setSaveMenu;

api.setSaveAsMenu = window._api.setSaveAsMenu;

api.setAddImagesMenu = window._api.setAddImagesMenu;

api.setAddFoldersMenu = window._api.setAddFoldersMenu;
