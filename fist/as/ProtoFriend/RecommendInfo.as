package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class RecommendInfo
	{
		public static const PROTO:String = "ProtoFriend.RecommendInfo";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var name:String;
		public var fig:String;
		public var level:int;
		public var grade:int;
		public var onlineTs:int;
		public var donationTs:int;
		public var battleTs:int;
		public var battle:int;
		public var heroId:Vector.<int>;
		public function RecommendInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			uid = undefined;
			name = undefined;
			fig = undefined;
			level = undefined;
			grade = undefined;
			onlineTs = undefined;
			donationTs = undefined;
			battleTs = undefined;
			battle = undefined;
			heroId = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.name = this.name;
			serializeObj.fig = this.fig;
			serializeObj.level = this.level;
			serializeObj.grade = this.grade;
			if(this.onlineTs!= undefined)
			{
				serializeObj.onlineTs = this.onlineTs;
			}
			if(this.donationTs!= undefined)
			{
				serializeObj.donationTs = this.donationTs;
			}
			if(this.battleTs!= undefined)
			{
				serializeObj.battleTs = this.battleTs;
			}
			if(this.battle!= undefined)
			{
				serializeObj.battle = this.battle;
			}
			serializeObj.heroId = [];
			for(var i:int = 0;i < this.heroId.length;i++)
			{
				serializeObj.heroId.push(this.heroId[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):RecommendInfo
		{
			uid = undefined;
			name = undefined;
			fig = undefined;
			level = undefined;
			grade = undefined;
			onlineTs = undefined;
			donationTs = undefined;
			battleTs = undefined;
			battle = undefined;
			heroId = new Vector.<int>();
			this.uid = msgObj.uid;
			this.name = msgObj.name;
			this.fig = msgObj.fig;
			this.level = msgObj.level;
			this.grade = msgObj.grade;
			if(msgObj.hasOwnProperty("onlineTs"))
			{
				this.onlineTs = msgObj.onlineTs;
			}
			if(msgObj.hasOwnProperty("donationTs"))
			{
				this.donationTs = msgObj.donationTs;
			}
			if(msgObj.hasOwnProperty("battleTs"))
			{
				this.battleTs = msgObj.battleTs;
			}
			if(msgObj.hasOwnProperty("battle"))
			{
				this.battle = msgObj.battle;
			}
			for(var i:int = 0;i < msgObj.heroId.length;i++)
			{
				this.heroId.push(msgObj.heroId[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RecommendInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}