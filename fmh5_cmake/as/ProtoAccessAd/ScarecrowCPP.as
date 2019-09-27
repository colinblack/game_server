package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class ScarecrowCPP
	{
		public static const PROTO:String = "ProtoAccessAd.ScarecrowCPP";
		public var package_root:*;
		public  var message:*;
		public var remainCnt:int;
		public var workEndTs:int;
		public var nextShowTs:int;
		public function ScarecrowCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			remainCnt = undefined;
			workEndTs = undefined;
			nextShowTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.remainCnt = this.remainCnt;
			serializeObj.workEndTs = this.workEndTs;
			serializeObj.nextShowTs = this.nextShowTs;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ScarecrowCPP
		{
			remainCnt = undefined;
			workEndTs = undefined;
			nextShowTs = undefined;
			this.remainCnt = msgObj.remainCnt;
			this.workEndTs = msgObj.workEndTs;
			this.nextShowTs = msgObj.nextShowTs;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ScarecrowCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}