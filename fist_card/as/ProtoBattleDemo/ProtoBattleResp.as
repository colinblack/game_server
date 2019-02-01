package com.sanguo.game.server.connectlogic.common.message.ProtoBattleDemo
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleResp
	{
		public static const PROTO:String = "ProtoBattleDemo.ProtoBattleResp";
		public var package_root:*;
		public  var message:*;
		public var next:int;
		public var info:Vector.<ProtoBattleDemoTurnInfo>;
		public function ProtoBattleResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			next = undefined;
			info = new Vector.<ProtoBattleDemoTurnInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.next = this.next;
			serializeObj.info = [];
			for(var i:int = 0;i < this.info.length;i++)
			{
				serializeObj.info.push(this.info[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleResp
		{
			next = undefined;
			info = new Vector.<ProtoBattleDemoTurnInfo>();
			this.next = msgObj.next;
			for(var i:int = 0;i < msgObj.info.length;i++)
			{
				this.info.push(new ProtoBattleDemoTurnInfo(package_root).unserialize(msgObj.info[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}