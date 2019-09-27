package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class SetFriendWorkerReq
	{
		public static const PROTO:String = "ProtoFriendWorker.SetFriendWorkerReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public var propsid:int;
		public var source:Vector.<int>;
		public function SetFriendWorkerReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
			propsid = undefined;
			source = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			if(this.propsid!= undefined)
			{
				serializeObj.propsid = this.propsid;
			}
			serializeObj.source = [];
			for(var i:int = 0;i < this.source.length;i++)
			{
				serializeObj.source.push(this.source[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetFriendWorkerReq
		{
			othuid = undefined;
			propsid = undefined;
			source = new Vector.<int>();
			this.othuid = msgObj.othuid;
			if(msgObj.hasOwnProperty("propsid"))
			{
				this.propsid = msgObj.propsid;
			}
			for(var i:int = 0;i < msgObj.source.length;i++)
			{
				this.source.push(msgObj.source[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetFriendWorkerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}