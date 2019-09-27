package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class SetFriendWorkerResp
	{
		public static const PROTO:String = "ProtoFriendWorker.SetFriendWorkerResp";
		public var package_root:*;
		public  var message:*;
		public var status:int;
		public function SetFriendWorkerResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			status = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.status = this.status;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetFriendWorkerResp
		{
			status = undefined;
			this.status = msgObj.status;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetFriendWorkerResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}