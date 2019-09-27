package com.sanguo.game.server.connectlogic.common.message.ProtoKeeper
{
	import laya.utils.Byte;
	public class KeeperInfoResp
	{
		public static const PROTO:String = "ProtoKeeper.KeeperInfoResp";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var level:int;
		public var exp:int;
		public var overTs:int;
		public var flag:int;
		public var commons:CommonItemsCPP;
		public var task:Vector.<KeeperTask>;
		public function KeeperInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			level = undefined;
			exp = undefined;
			overTs = undefined;
			flag = undefined;
			commons = undefined;
			task = new Vector.<KeeperTask>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.level = this.level;
			serializeObj.exp = this.exp;
			serializeObj.overTs = this.overTs;
			serializeObj.flag = this.flag;
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			serializeObj.task = [];
			for(var i:int = 0;i < this.task.length;i++)
			{
				serializeObj.task.push(this.task[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):KeeperInfoResp
		{
			id = undefined;
			level = undefined;
			exp = undefined;
			overTs = undefined;
			flag = undefined;
			commons = undefined;
			task = new Vector.<KeeperTask>();
			this.id = msgObj.id;
			this.level = msgObj.level;
			this.exp = msgObj.exp;
			this.overTs = msgObj.overTs;
			this.flag = msgObj.flag;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			for(var i:int = 0;i < msgObj.task.length;i++)
			{
				this.task.push(new KeeperTask(package_root).unserialize(msgObj.task[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):KeeperInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}