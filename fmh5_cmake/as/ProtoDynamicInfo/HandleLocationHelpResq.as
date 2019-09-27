package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class HandleLocationHelpResq
	{
		public static const PROTO:String = "ProtoDynamicInfo.HandleLocationHelpResq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var newtypeid:int;
		public function HandleLocationHelpResq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			newtypeid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.newtypeid = this.newtypeid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):HandleLocationHelpResq
		{
			id = undefined;
			newtypeid = undefined;
			this.id = msgObj.id;
			this.newtypeid = msgObj.newtypeid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):HandleLocationHelpResq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}