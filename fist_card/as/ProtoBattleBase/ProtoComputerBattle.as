package com.sanguo.game.server.connectlogic.common.message.ProtoBattleBase
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoComputerBattle
	{
		public static const PROTO:String = "ProtoBattleBase.ProtoComputerBattle";
		public var package_root:*;
		public  var message:*;
		public var nextuser:int;
		public var outcards:Vector.<ProtoComputerCards>;
		public var winUid:int;
		public var point:int;
		public function ProtoComputerBattle(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			nextuser = undefined;
			outcards = new Vector.<ProtoComputerCards>();
			winUid = undefined;
			point = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.nextuser = this.nextuser;
			serializeObj.outcards = [];
			for(var i:int = 0;i < this.outcards.length;i++)
			{
				serializeObj.outcards.push(this.outcards[i].serialize());
			}
			if(this.winUid!= undefined)
			{
				serializeObj.winUid = this.winUid;
			}
			serializeObj.point = this.point;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoComputerBattle
		{
			nextuser = undefined;
			outcards = new Vector.<ProtoComputerCards>();
			winUid = undefined;
			point = undefined;
			this.nextuser = msgObj.nextuser;
			for(var i:int = 0;i < msgObj.outcards.length;i++)
			{
				this.outcards.push(new ProtoComputerCards(package_root).unserialize(msgObj.outcards[i]));
			}
			if(msgObj.hasOwnProperty("winUid"))
			{
				this.winUid = msgObj.winUid;
			}
			this.point = msgObj.point;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoComputerBattle
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}