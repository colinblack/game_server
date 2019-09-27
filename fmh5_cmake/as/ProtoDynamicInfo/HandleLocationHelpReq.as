package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class HandleLocationHelpReq
	{
		public static const PROTO:String = "ProtoDynamicInfo.HandleLocationHelpReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var typeid:int;
		public function HandleLocationHelpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			typeid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.typeid = this.typeid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):HandleLocationHelpReq
		{
			id = undefined;
			typeid = undefined;
			this.id = msgObj.id;
			this.typeid = msgObj.typeid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):HandleLocationHelpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}