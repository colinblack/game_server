package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class RequestForbidTS
	{
		public static const PROTO:String = "Admin.RequestForbidTS";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public function RequestForbidTS(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestForbidTS
		{
			uid = undefined;
			this.uid = msgObj.uid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestForbidTS
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}