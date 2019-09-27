package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class Tutorialstage
	{
		public static const PROTO:String = "User.Tutorialstage";
		public var package_root:*;
		public  var message:*;
		public var tutorialStage:int;
		public function Tutorialstage(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			tutorialStage = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.tutorialStage = this.tutorialStage;
			return serializeObj;
		}
		public function unserialize(msgObj:*):Tutorialstage
		{
			tutorialStage = undefined;
			this.tutorialStage = msgObj.tutorialStage;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):Tutorialstage
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}