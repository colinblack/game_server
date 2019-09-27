package com.sanguo.game.server.connectlogic.common.message.ProtoNotify
{
	import laya.utils.Byte;
	public class GetNotifyReq
	{
		public static const PROTO:String = "ProtoNotify.GetNotifyReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function GetNotifyReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetNotifyReq
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetNotifyReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}