package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class PackBoxReq
	{
		public static const PROTO:String = "ProtoShipping.PackBoxReq";
		public var package_root:*;
		public  var message:*;
		public var boxid:int;
		public var type:int;
		public function PackBoxReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			boxid = undefined;
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.boxid = this.boxid;
			serializeObj.type = this.type;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PackBoxReq
		{
			boxid = undefined;
			type = undefined;
			this.boxid = msgObj.boxid;
			this.type = msgObj.type;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PackBoxReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}