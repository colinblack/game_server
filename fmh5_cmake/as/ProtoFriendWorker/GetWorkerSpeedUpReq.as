package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class GetWorkerSpeedUpReq
	{
		public static const PROTO:String = "ProtoFriendWorker.GetWorkerSpeedUpReq";
		public var package_root:*;
		public  var message:*;
		public function GetWorkerSpeedUpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetWorkerSpeedUpReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetWorkerSpeedUpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}