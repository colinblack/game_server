package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class CSSetFriendWorkerResp
	{
		public static const PROTO:String = "ProtoFriendWorker.CSSetFriendWorkerResp";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public var myuid:int;
		public var stauts:int;
		public function CSSetFriendWorkerResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
			myuid = undefined;
			stauts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			serializeObj.myuid = this.myuid;
			serializeObj.stauts = this.stauts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSSetFriendWorkerResp
		{
			othuid = undefined;
			myuid = undefined;
			stauts = undefined;
			this.othuid = msgObj.othuid;
			this.myuid = msgObj.myuid;
			this.stauts = msgObj.stauts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSSetFriendWorkerResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}