package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class GetWorkerSpeedUpResp
	{
		public static const PROTO:String = "ProtoFriendWorker.GetWorkerSpeedUpResp";
		public var package_root:*;
		public  var message:*;
		public var friendworker:Vector.<FriendWorkerCPP>;
		public function GetWorkerSpeedUpResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			friendworker = new Vector.<FriendWorkerCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.friendworker = [];
			for(var i:int = 0;i < this.friendworker.length;i++)
			{
				serializeObj.friendworker.push(this.friendworker[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetWorkerSpeedUpResp
		{
			friendworker = new Vector.<FriendWorkerCPP>();
			for(var i:int = 0;i < msgObj.friendworker.length;i++)
			{
				this.friendworker.push(new FriendWorkerCPP(package_root).unserialize(msgObj.friendworker[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetWorkerSpeedUpResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}