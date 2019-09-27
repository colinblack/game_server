package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class NewShareCPP
	{
		public static const PROTO:String = "ProtoActivity.NewShareCPP";
		public var package_root:*;
		public  var message:*;
		public var nextShareTs:int;
		public var remainShareCnt:int;
		public function NewShareCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			nextShareTs = undefined;
			remainShareCnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.nextShareTs = this.nextShareTs;
			serializeObj.remainShareCnt = this.remainShareCnt;
			return serializeObj;
		}
		public function unserialize(msgObj:*):NewShareCPP
		{
			nextShareTs = undefined;
			remainShareCnt = undefined;
			this.nextShareTs = msgObj.nextShareTs;
			this.remainShareCnt = msgObj.remainShareCnt;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NewShareCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}